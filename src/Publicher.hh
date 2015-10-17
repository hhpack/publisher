<?hh //strict

namespace hhpack\publisher;

interface Publicher<T as Message>
{
    public function registerSubscriber(Subscribable<T> $subscriber) : void;
    public function unregisterSubscriber(Subscribable<T> $subscriber) : void;
}
