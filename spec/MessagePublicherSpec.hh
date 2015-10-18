<?hh //partial

namespace hhpack\publisher\spec;

use hhpack\publisher\MessagePublicher;
use hhpack\publisher\spec\fixtures\DomainMessage;
use hhpack\publisher\spec\fixtures\DomainSubscriber;

describe(MessagePublicher::class, function () {

  describe('registerSubscriber()', function () {
    beforeEach(function() {
      $this->publisher = new MessagePublicher();
    });
    it('register subscriber', function () {
      $this->publisher->registerSubscriber(new DomainSubscriber());
      expect($this->publisher->hasSubscriber())->toBeTrue();
    });
  });

  describe('unregisterSubscriber()', function () {
    beforeEach(function() {
      $this->publisher = new MessagePublicher();
    });
    it('unregister subscriber', function () {
      $subscriber = new DomainSubscriber();
      $this->publisher->registerSubscriber($subscriber);
      $this->publisher->unregisterSubscriber($subscriber);
      expect($this->publisher->hasSubscriber())->toBeFalse();
    });
  });

});
