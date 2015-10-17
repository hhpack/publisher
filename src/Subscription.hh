<?hh //strict

namespace hhpack\publisher;

interface Subscription<T>
{
    public function receive(T $message) : void;
}
