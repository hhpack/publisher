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

final class SubscriptionCollector<T as Message>
{

    private ReflectionClass $class;

    public function __construct(
        private Subscribable<T> $subscriber
    )
    {
        $this->class = new ReflectionClass($subscriber);
    }

    public function collectByType(string $type) : SubscriptionRegistry<T>
    {
        $matcher = new ArgumentTypeMatcher($type);
        $registry = new SubscriptionRegistry($this->subscriber);

        foreach ($this->methods() as $method) {
            $result = $matcher->matches($method);

            if ($result->unmatched()) {
                continue;
            }
            $registry->registerByMatchedResult($result);
        }

        return $registry;
    }

    private function methods() : Iterator<ReflectionMethod>
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
