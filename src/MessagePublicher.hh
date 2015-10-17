<?hh //strict

namespace hhpack\publisher;

final class MessagePublicher implements Publicher<Message>
{

    public function __construct(
        private Vector<Agent<Message>> $subscribers = Vector {}
    )
    {
    }

    public function registerSubscriber(Subscribable<Message> $subscriber) : void
    {
        $this->subscribers->add(new SubscribeAgent($subscriber));
    }

    public function unregisterSubscriber(Subscribable<Message> $subscriber) : void
    {
        foreach ($this->subscribers->getIterator() as $key => $agent) {
            if ($agent->matches($subscriber) === false) {
                continue;
            }
            $this->subscribers->removeKey($key);
        }
    }

    public function publish(Message $message) : void
    {
        foreach ($this->subscribers->items() as $subscriber) {
            $subscriber->receive($message);
        }
    }

}
