<?hh //strict

/**
 * This file is part of HHPack\Publisher.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace HHPack\Publisher;

use ReflectionClass;
use ReflectionMethod;
use ReflectionParameter;
use LogicException;

final class SubscriptionCollector<T as Message> {

  private ReflectionClass $class;

  public function __construct(private Subscribable<T> $subscriber) {
    $this->class = new ReflectionClass($subscriber);
  }

  public function collectByType(string $type): SubscriptionRegistry<T> {
    $matcher = new ArgumentTypeMatcher($type);
    $registry = new SubscriptionRegistry($this->subscriber);

    foreach ($this->methods() as $method) {
      if ($matcher->matches($method) === false) {
        continue;
      }

      $subscription = $this->subscriptionFrom($method);
      $subscription->registerTo($registry);
    }

    return $registry;
  }

  private function methods(): Iterator<ReflectionMethod> {
    $methods = $this->class->getMethods(ReflectionMethod::IS_PUBLIC);

    foreach ($methods as $method) {
      if ($method->isAbstract() ||
          $method->isStatic() ||
          $method->isConstructor() ||
          $method->isDestructor()) {
        continue;
      }
      yield $method;
    }
  }

  private function subscriptionFrom(
    ReflectionMethod $method,
  ): Subscription<T> {
    $parameter = ImmVector::fromItems($method->getParameters())->firstValue();
    $typeName = $parameter?->getClass()?->getName();

    if ($typeName === null) {
      throw new LogicException(
        sprintf(
          '%s::%s does not receive the argument',
          $method->getDeclaringClass()->getName(),
          $method->getName(),
        ),
      );
    }

    return
      new InvokeSubscription($typeName, Pair {$this->subscriber, $method});
  }

}
