<?hh //strict

/**
 *	HHVM port of Félix Girault's Cascade (https://github.com/felixgirault/cascade)
 *	@author Matthias Jouan <matthias.jouan@gmail.com>
 *	@license FreeBSD License (http://opensource.org/licenses/BSD-2-Clause)
 */
namespace Cascade;

use BadMethodCallException;



/**
 *	A lightweight API to filter values.
 */
class Cascade {

	/**
	 *	Filters.
	 *
	 *	@var Vector<(function(mixed):mixed)>
	 */
	protected Vector<(function(mixed):mixed)> $filters;



	/**
	 *	Constructor.
	 *
	 *	@param Vector<(function(mixed):mixed)> $filters Filters.
	 */
	public function __construct(Vector<(function(mixed):mixed)> $filters = Vector{}) {
		$this->filters = $filters;
	}



	/**
	 *	Returns all filters.
	 *
	 *	@return Vector<(function(mixed):mixed)> Filters.
	 */
	public function filters() : Vector<(function(mixed):mixed)> {
		return $this->filters;
	}



	/**
	 *	Sets all filters.
	 *
	 *	@param Vector<(function(mixed):mixed)> $filters Filters.
	 *	@return this.
	 */
	public function setFilters(Vector<(function(mixed):mixed)> $filters) : this {
		$this->filters = $filters;
		return $this;
	}



	/**
	 *	Adds a filter.
	 *
	 *	@param callable $filter Filter.
	 *	@return Cascade Instance.
	 */
	public function addFilter((function(mixed):mixed) $filter) : this {
		$this->filters[] = $filter;
		return $this;
	}



	/**
	 *	Filters the given value.
	 *
	 *	@param mixed $value Value.
	 *	@param mixed ... Additional arguments to pass to the filters.
	 *	@return mixed Filtered value.
	 */
	public function filter(...) : mixed {
		$arguments = func_get_args();

		if (count($arguments) === 0) {
			throw new BadMethodCallException(
				'A value to filter is required.'
			);
		}

		$value = &$arguments[0];

		foreach ($this->filters as $filter) {
			$value = call_user_func_array($filter, $arguments);
		}

		return $value;
	}
}
