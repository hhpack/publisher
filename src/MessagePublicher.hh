<?hh //strict

namespace hhpack\publisher;

final class MessagePublicher implements Publicher<Message>
{

    public function __construct(
        private Vector<Subscriber<Message>> $subscribers = Vector {}
    )
    {
    }

    public function registerSubscriber(Subscriber<Message> $subscriber) : void
    {
        $this->subscribers->add($subscriber);
    }

    public function publish(Message $message) : void
    {
        foreach ($this->subscribers->items() as $subscriber) {
            $subscriber->receive($message);
        }
    }

}
