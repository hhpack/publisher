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

final class SubscribeAgent<T as Message> implements Agent<T>
{

    private SubscriptionMap<T> $subscriptions = Map {};

    public function __construct(
        private Subscribable<T> $subscriber
    )
    {
        $methods = $this->receiverMethods($subscriber);

        foreach ($methods->lazy() as $typeName => $methodName) {
            $subscriptions = $this->subscriptions->get($typeName);

            if ($subscriptions === null) {
                $subscriptions = Vector {};
            }
            $subscriptions->add(new InvokeSubscription( Pair { $this->subscriber, $methodName }));

            $this->subscriptions->set($typeName, $subscriptions);
        }
    }

    public function matches(Subscribable<T> $subscriber) : bool
    {
        return $this->subscriber === $subscriber;
    }

    public function receive(T $message) : void
    {
        $nameOfType = get_class($message);

        if ($this->subscriptions->containsKey($nameOfType) === false) {
            return;
        }
        $subscriptions = $this->subscriptions->at($nameOfType);

        foreach ($subscriptions->items() as $subscription) {
            $subscription->receive($message);
        }
    }

    private function receiverMethods(Subscribable<T> $subscriber) : ImmMap<string, string>
    {
        $class = new ReflectionClass($subscriber);
        $methods = $class->getMethods(ReflectionMethod::IS_PUBLIC);
        $results = Map {};

        foreach ($methods as $method) {
            if ($method->getNumberOfRequiredParameters() <= 0) {
                continue;
            }

            $parameters = $method->getParameters();
            $parameter = $parameters[0];

            $type = $parameter->getClass();

            if ($type === null) {
                continue;
            }

            $typeName = $type->getName();

            if ($type->implementsInterface(Message::class) === false) {
                continue;
            }

            $results->set($typeName, $method->getName());
        }

        return $results->toImmMap();
    }

}
