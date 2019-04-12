/**
 * This file is part of HHPack\Publisher.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace HHPack\Publisher;

interface Subscription<T> {
  public function type(): string;
  public function receive(T $message): Awaitable<void>;
  public function registerTo(Registry<T> $registry): void;
}
