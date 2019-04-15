namespace HHPack\Publisher\Example;

require_once __DIR__.'/../vendor/hh_autoload.hh';

use HHPack\Publisher\MessagePublisher;
use HHPack\Publisher\Example\DomainMessage;
use HHPack\Publisher\Example\DomainMessageSubscriber;

<<__EntryPoint>>
async function publisher_main(): Awaitable<noreturn> {
  $publisher = new MessagePublisher();
  $publisher->registerSubscriber(new DomainMessageSubscriber());

  await $publisher->publish(new DomainMessage("send message!!"));

  exit(0);
}
