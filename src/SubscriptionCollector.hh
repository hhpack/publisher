<?hh //strict

/**
 * This file is part of hhpack\publisher.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace hhpack\publisher;

use ReflectionClass;
use ReflectionMethod;
use ReflectionParameter;
use Generator;

final class SubscriptionCollector<T as Message>
{

    private ReflectionClass $class;

    public function __construct(
        private Subscribable<T> $target
    )
    {
        $this->class = new ReflectionClass($target);
    }

    public function collectByType(string $type) : SubscriptionMap<T>
    {
        $registry = Map {};
        $matcher = new ArgumentTypeMatcher($type);

        foreach ($this->methods() as $method) {
            $result = $matcher->matches($method);

            if ($result->unmatched()) {
                continue;
            }

            $subscriptions = $registry->get($result->getArgumentType());

            if ($subscriptions === null) {
                $subscriptions = Vector {};
            }
            $subscriptions->add(new InvokeSubscription( Pair { $this->target, $result->getName() }));

            $registry->set($result->getArgumentType(), $subscriptions);
        }

        return $registry;
    }

    private function methods() : Generator<int, ReflectionMethod, void>
    {
        $methods = $this->class->getMethods(ReflectionMethod::IS_PUBLIC);

        foreach ($methods as $method) {
            if ($method->isAbstract() || $method->isStatic()
                || $method->isConstructor() || $method->isDestructor()) {
                continue;
            }
            yield $method;
        }
    }

}
