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
        $class = new ReflectionClass($subscriber);
        $methods = $class->getMethods(ReflectionMethod::IS_PUBLIC);

        foreach ($methods as $method) {
            $parameters = $method->getParameters();

            if (count($parameters) <= 0) {
                continue;
            }

            $parameter = $parameters[0];

            $type = $parameter->getClass();

            if ($type === null) {
                continue;
            }

            $typeName = $type->getName();

            if ($type->implementsInterface(Message::class) === false) {
                continue;
            }

            $subscriptions = $this->subscriptions->get($typeName);

            if ($subscriptions === null) {
                $subscriptions = Vector {};
            }
            $subscriptions->add(new InvokeSubscription( Pair { $this->subscriber, $method->getName() }));

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

}
