<?hh //strict

namespace hhpack\publisher;

final class MessagePublicher<T as Message> implements Publicher<T>
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

}
