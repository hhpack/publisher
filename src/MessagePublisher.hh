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

final class MessagePublisher<T as Message> implements Publisher<T>
{

    private Vector<Agent<T>> $agents;

    public function __construct(
        ?Traversable<Subscribable<T>> $subscribers
    )
    {
        $mapper = ($subscriber) ==> new SubscribeAgent($subscriber);
        $this->agents = Vector::fromItems($subscribers)->map($mapper);
    }

    public function registerSubscriber(Subscribable<T> $subscriber) : void
    {
        $this->agents->add(new SubscribeAgent($subscriber));
    }

    public function unregisterSubscriber(Subscribable<T> $subscriber) : void
    {
        foreach ($this->agents->lazy() as $key => $agent) {
            if ($agent->matches($subscriber) === false) {
                continue;
            }
            $this->agents->removeKey($key);
        }
    }

    public function publish(T $message) : void
    {
        foreach ($this->agents->items() as $agent) {
            $agent->receive($message);
        }
    }

    public function hasSubscriber() : bool
    {
        return $this->agents->isEmpty() === false;
    }

}
