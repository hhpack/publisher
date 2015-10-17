<?hh //strict

namespace hhpack\publisher;

interface Publicher<T>
{
    public function registerSubscriber(Subscribable<T> $subscriber) : void;
    public function unregisterSubscriber(Subscribable<T> $subscriber) : void;
}
