<?hh //strict

namespace hhhack\publisher;

interface Subscriber<T as Message>
{
    public function subscribe(Publicher<T> $publicher) : void;
    public function receive(T $message) : void;
}
