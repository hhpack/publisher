<?hh //strict

namespace hhpack\publisher;

interface Agent<T>
{
    public function receive(T $message) : void;
    public function matches(Subscribable<T> $subscriber) : bool;
}
