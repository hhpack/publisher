<?hh //strict

namespace hhpack\publisher;

interface Publicher<T as Message>
{
    public function registerSubscriber(Subscriber<T> $subscriber) : void;
}
