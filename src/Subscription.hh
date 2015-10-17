<?hh //strict

namespace hhhack\publisher;

interface Subscription<T as Message>
{
    public function receive(T $message) : void;
}
