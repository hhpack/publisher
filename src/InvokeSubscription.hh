<?hh //strict

namespace hhhack\publisher;

final class InvokeSubscription implements Subscription<Message>
{

    public function __construct(
        private Pair<Subscribable<Message>, string> $proxy
    )
    {
    }

    public function receive(Message $message) : void
    {
        $arguments = $this->proxy->toArray();
        call_user_func_array($arguments, [ $message ]);
    }

}
