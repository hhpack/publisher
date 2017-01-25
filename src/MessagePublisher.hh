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

final class MessagePublisher<T as Message> implements Publisher<T>
{

    private Vector<Agent<T>> $agents;

    public function __construct(
        Traversable<Subscribable<T>> $subscribers = []
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

    public async function publish(T $message) : Awaitable<void>
    {
        $awaitables = $this->agents->map(($agent) ==> {
            return $agent->receive($message);
        });
        await \HH\Asio\v($awaitables);
    }

    public function hasSubscriber() : bool
    {
        return $this->agents->isEmpty() === false;
    }

}
