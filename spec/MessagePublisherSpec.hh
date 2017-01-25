<?hh //partial

namespace HHPack\Publisher\Spec;

use HHPack\Publisher\MessagePublisher;
use HHPack\Publisher\Spec\Fixtures\DomainMessage;
use HHPack\Publisher\Spec\Fixtures\DomainSubscriber;

describe(MessagePublisher::class, function () {

  describe('registerSubscriber()', function () {
    beforeEach(function() {
      $this->publisher = new MessagePublisher();
    });
    it('register subscriber', function () {
      $this->publisher->registerSubscriber(new DomainSubscriber());
      expect($this->publisher->hasSubscriber())->toBeTrue();
    });
  });

  describe('unregisterSubscriber()', function () {
    beforeEach(function() {
      $this->publisher = new MessagePublisher();
    });
    it('unregister subscriber', function () {
      $subscriber = new DomainSubscriber();
      $this->publisher->registerSubscriber($subscriber);
      $this->publisher->unregisterSubscriber($subscriber);
      expect($this->publisher->hasSubscriber())->toBeFalse();
    });
  });

  describe('publish()', function () {
    beforeEach(function() {
      $this->subscriber = new DomainSubscriber();
      $this->publisher = new MessagePublisher();
      $this->publisher->registerSubscriber($this->subscriber);
    });
    it('published message to subscriber', function () {
      $this->publisher->publish(new DomainMessage());
      expect($this->subscriber->calledCount())->toBe(1);
    });
  });

});
