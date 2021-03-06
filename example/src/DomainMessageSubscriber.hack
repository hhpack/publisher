namespace HHPack\Publisher\Example;

use HHPack\Publisher\Message;
use HHPack\Publisher\Subscribable;

final class DomainMessageSubscriber implements Subscribable<Message> {

  public async function onDomainMessage(
    DomainMessage $message,
  ): Awaitable<void> {
    \printf("%s", $message->description());
  }

}
