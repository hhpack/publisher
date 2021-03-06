publisher
================================================

Simple implementation of Pub/Sub for Hack.

[![Latest Stable Version](https://poser.pugx.org/hhpack/publisher/v/stable)](https://packagist.org/packages/hhpack/publisher)
[![CircleCI](https://circleci.com/gh/hhpack/publisher/tree/master.svg?style=svg)](https://circleci.com/gh/hhpack/publisher/tree/master)
[![Dependency Status](https://www.versioneye.com/user/projects/562247cb36d0ab0016000b18/badge.svg?style=flat)](https://www.versioneye.com/user/projects/562247cb36d0ab0016000b18)
[![License](https://poser.pugx.org/hhpack/publisher/license)](https://packagist.org/packages/hhpack/publisher)

Basic usage
------------------------------------------------

Usage is very simple, You just implement **Message** the **Subscriber**.  
The following are register to **MessagePublisher** and just publish a message.

```hack
namespace domain;

use HHPack\Publisher\Message;
use HHPack\Publisher\Subscribable;
use HHPack\Publisher\MessagePublisher;

final class DomainMessage implements Message
{
}

final class DomainMessageSubscriber implements Subscribable<Message>
{
  public async function onDomainMessage(DomainMessage $message) : Awaitable<void>
  {
    await async_task1();
    await async_task2();
  }
}

$publisher = new MessagePublisher();
$publisher->registerSubscriber(new DomainMessageSubscriber());

await $publisher->publish(new DomainMessage());
```

Run the test
------------------------------------------------

You can run the test with the following command.

	composer install
	composer test
