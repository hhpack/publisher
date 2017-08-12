<?hh //strict

namespace HHPack\Publisher\Test\Fixtures;

use HHPack\Publisher\{ Message, Subscribable };

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
