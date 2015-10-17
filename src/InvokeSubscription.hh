<?hh //strict

namespace hhpack\publisher;

final class InvokeSubscription<T as Message> implements Subscription<T>
{

    public function __construct(
        private InvokeTarget<T> $invokeTarget
    )
    {
    }

    public function receive(T $message) : void
    {
        $callback = $this->invokeTarget->toArray();
        call_user_func_array($callback, [ $message ]);
    }

}
