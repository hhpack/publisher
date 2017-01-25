<?hh //partial

namespace HHPack\Publisher\Spec;

use HHPack\Publisher\InvokeSubscription;
use HHPack\Publisher\Spec\Fixtures\DomainMessage;
use HHPack\Publisher\Spec\Fixtures\DomainSubscriber;
use HHPack\Publisher\Spec\Fixtures\AsyncDomainSubscriber;
use ReflectionMethod;

describe(InvokeSubscription::class, function () {
  describe('receive()', function () {
    context('when sync', function () {
      beforeEach(function () {
        $this->subscriber = new DomainSubscriber();
        $this->method = new ReflectionMethod( DomainSubscriber::class, 'invoke');
        $this->invoker = Pair { $this->subscriber, $this->method };
        $this->subscription = new InvokeSubscription(DomainMessage::class, $this->invoker);
      });
      it('call once the method of target', function() {
        $this->subscription->receive(new DomainMessage());
        expect($this->subscriber->calledCount())->toBe(1);
      });
    });
    context('when async', function () {
      beforeEach(function () {
        $this->subscriber = new AsyncDomainSubscriber();
        $this->method = new ReflectionMethod( AsyncDomainSubscriber::class, 'invoke');
        $this->invoker = Pair { $this->subscriber, $this->method };
        $this->subscription = new InvokeSubscription(DomainMessage::class, $this->invoker);
      });
      it('call once the method of target', async function() {
        await $this->subscription->receive(new DomainMessage());
        expect($this->subscriber->calledCount())->toBe(1);
      });
    });
  });
});
