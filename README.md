Cascade
=======

A lightweight API to filter values.

Installation
------------

```sh
composer install fg/cascade
```

Usage
-----

Filtering a value:

```php
$Cascade = new Cascade\Cascade([
	function($value) {
		return $value + $value;
	},
	function($value) {
		return $value * $value;
	}
]);

echo $Cascade->filter(2); // 16
```

Filtering a value depending on additionnal arguments:

```php
$Cascade = new Cascade\Cascade([
	function($value, $factor) {
		return $value * $factor;
	}
]);

echo $Cascade->filter(2, 10); // 20
```

Filtering a value with a filter object:

```php
class SquareFilter {
	public function __invoke($value) {
		return $value * $value;
	}
}

$Cascade = new Cascade\Cascade([
	new SquareFilter()
]);

echo $Cascade->filter(2); // 4
```

API
---

```php
// constructor
$Cascade = new Cascade\Cascade();
$Cascade = new Cascade\Cascade($filters);

// accessors for the list of filters
$Cascade->filters();
$Cascade->setFilters($filters);
$Cascade->addFilter($filter);

// filter
$Cascade->filter($value [, $args...]);
```
