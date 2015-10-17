<?hh //strict

namespace hhpack\publisher;

interface Subscription<T as Message>
{
    public function receive(T $message) : void;
}
