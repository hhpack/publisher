<?hh //partial

namespace hhpack\publisher\spec;

use ReflectionMethod;
use hhpack\publisher\Message;
use hhpack\publisher\ArgumentTypeMatcher;
use hhpack\publisher\spec\fixtures\Method;

describe(ArgumentTypeMatcher::class, function () {
  beforeEach(function () {
    $this->matcher = ArgumentTypeMatcher::fromString(Message::class);
  });
  describe('matches()', function () {
    context('when no arguments', function () {
      it('return unmathced result', function() {
        $method = new ReflectionMethod(Method::class, 'noParameters');
        $result = $this->matcher->matches($method);
        expect($result->unmatched())->toBeTrue();
      });
    });
    context('when one arguments', function () {
      it('return unmathced result', function() {
        $method = new ReflectionMethod(Method::class, 'oneParameter');
        $result = $this->matcher->matches($method);
        expect($result->unmatched())->toBeTrue();
      });
    });
    context('when two arguments', function () {
      it('return unmathced result', function() {
        $method = new ReflectionMethod(Method::class, 'twoParameter');
        $result = $this->matcher->matches($method);
        expect($result->unmatched())->toBeTrue();
      });
    });
    context('when one arguments and message type', function () {
      it('return mathced result', function() {
        $method = new ReflectionMethod(Method::class, 'oneParameterAndMessage');
        $result = $this->matcher->matches($method);
        expect($result->unmatched())->toBeFalse();
      });
    });
    context('when two arguments and message type', function () {
      it('return unmathced result', function() {
        $method = new ReflectionMethod(Method::class, 'twoParameterAndMessage');
        $result = $this->matcher->matches($method);
        expect($result->unmatched())->toBeTrue();
      });
    });
  });
});
