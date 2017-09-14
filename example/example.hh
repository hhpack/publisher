<?hh //partial

namespace HHPack\Publisher\Example;

require_once __DIR__.'/../vendor/autoload.php';

use HHPack\Publisher\MessagePublisher;
use HHPack\Publisher\Example\DomainMessage;
use HHPack\Publisher\Example\DomainMessageSubscriber;

async function publisher_main(): Awaitable<void> {
  $publisher = new MessagePublisher();
  $publisher->registerSubscriber(new DomainMessageSubscriber());

  await $publisher->publish(new DomainMessage());
}
\HH\Asio\join(publisher_main());
