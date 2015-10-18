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

final class SubscriptionRegistry<T as Message>
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

    public function registerByMatchedResult(MatchedResult $result) : void
    {
        $subscriptions = $this->registry->get($result->getArgumentType());

        if ($subscriptions === null) {
            $subscriptions = Vector {};
        }
        $subscriptions->add(new InvokeSubscription( Pair { $this->subscriber, $result->getName() }));

        $this->registry->set($result->getArgumentType(), $subscriptions);
    }

}
