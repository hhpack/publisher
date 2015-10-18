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

    private SubscriptionRegistry<T> $subscriptions;

    public function __construct(
        private Subscribable<T> $subscriber
    )
    {
        $collector = new SubscriptionCollector($subscriber);
        $this->subscriptions = $collector->collectByType(Message::class);
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
