<?hh //strict

namespace hhpack\publisher;

final class InvokeSubscription<T as Message> implements Subscription<T>
{

    public function __construct(
        private Pair<Subscribable<T>, string> $proxy
    )
    {
    }

    public function receive(T $message) : void
    {
        $arguments = $this->proxy->toArray();
        call_user_func_array($arguments, [ $message ]);
    }

}
