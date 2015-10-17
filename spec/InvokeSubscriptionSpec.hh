<?hh //partial

namespace hhpack\publisher\spec;

use hhpack\publisher\InvokeSubscription;
use hhpack\publisher\spec\fixtures\DomainMessage;
use hhpack\publisher\spec\fixtures\DomainSubscriber;

describe(InvokeSubscription::class, function () {
  beforeEach(function () {
    $this->subscriber = new DomainSubscriber();
    $this->subscription = new InvokeSubscription(Pair { $this->subscriber, 'invoke' });
  });
  describe('receive()', function () {
    it('call once the method of target', function() {
      $this->subscription->receive(new DomainMessage());
      expect($this->subscriber->calledCount())->toBe(1);
    });
  });
});
