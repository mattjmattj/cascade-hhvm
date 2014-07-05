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

echo $Cascade->filter(2);
```

```
int(16)
```

Filtering a value depending on additionnal arguments:

```php
$Cascade = new Cascade\Cascade([
	function($value, $factor) {
		return $value * $factor;
	}
]);

echo $Cascade->filter(2, 10);
```

```
int(20)
```

Filtering a value with a filter object:

```php
class SquareFilter {
	public function filter($value) {
		return $value * $value;
	}
}

$Cascade = new Cascade\Cascade([
	new SquareFilter()
]);

echo $Cascade->filter(2);
```

```
int(4)
```

API
---

```php
// constructor
$Cascade = new Cascade\Cascade($filters, $method);

// accessors for the list of filters
$Cascade->filters();
$Cascade->setFilters($filters);
$Cascade->addFilter($filter);

// accessors for the filtering method, i.e. the method that will be called on
// filter objects.
$Cascade->method();
$Cascade->setMethod($method);

// filter
$Cascade->filter($value [, $args...]);
```
