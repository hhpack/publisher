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

final class SubscriptionRegistry<T as Message> implements Registry<T>
{

    private SubscriptionMap<T> $registry;

    public function __construct(
        private Subscribable<T> $subscriber
    )
    {
        $this->registry = Map {};
    }

    public function containsKey(string $key) : bool
    {
        return $this->registry->containsKey($key);
    }

    public function at(string $key) : Vector<Subscription<T>>
    {
        return $this->registry->at($key);
    }

    public function register(Subscription<T> $subscription) : void
    {
        $subscriptions = $this->registry->get( $subscription->type() );

        if ($subscriptions === null) {
            $subscriptions = Vector {};
        }
        $subscriptions->add($subscription);

        $this->registry->set($subscription->type(), $subscriptions);
    }

}
