<?hh //strict

namespace HHPack\Publisher\Test\Fixtures;

use HHPack\Publisher\{Message, Subscribable};

final class AsyncDomainSubscriber implements Subscribable<Message> {

  private int $count = 0;

  public async function invoke(DomainMessage $message): Awaitable<void> {
    $this->count++;
  }

  public function calledCount(): int {
    return $this->count;
  }

}
