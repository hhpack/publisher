<?hh //strict

namespace HHPack\Publisher\Example;

use HHPack\Publisher\Message;

final class DomainMessage implements Message {
  public function __construct(private string $description) {
  }
  public function description(): string {
    return $this->description;
  }
}
