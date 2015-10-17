<?hh //strict

namespace hhpack\publisher;

final class MessagePublicher<T as Message> implements Publicher<T>
{

    public function __construct(
        private Vector<Agent<T>> $subscribers = Vector {}
    )
    {
    }

    public function registerSubscriber(Subscribable<T> $subscriber) : void
    {
        $this->subscribers->add(new SubscribeAgent($subscriber));
    }

    public function unregisterSubscriber(Subscribable<T> $subscriber) : void
    {
        foreach ($this->subscribers->getIterator() as $key => $agent) {
            if ($agent->matches($subscriber) === false) {
                continue;
            }
            $this->subscribers->removeKey($key);
        }
    }

    public function publish(T $message) : void
    {
        foreach ($this->subscribers->items() as $subscriber) {
            $subscriber->receive($message);
        }
    }

}
