<?hh //strict

namespace hhpack\publisher\spec\fixtures;

use hhpack\publisher\Message;
use hhpack\publisher\Subscribable;

final class DomainSubscriber implements Subscribable<Message>
{

    private int $count = 0;

    public function invoke(DomainMessage $message) : void
    {
        $this->count++;
    }

    public function calledCount() : int
    {
        return $this->count;
    }

}
