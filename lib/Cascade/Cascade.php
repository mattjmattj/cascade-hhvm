<?php

/**
 *	@author Félix Girault <felix.girault@gmail.com>
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
	 *	@var array
	 */
	protected $_filters = '';



	/**
	 *	Filtering method to call on filter objects.
	 *
	 *	@var string
	 */
	protected $_method = '';



	/**
	 *	Constructor.
	 *
	 *	@param array $filters Filters.
	 *	@param string $method Filtering method.
	 */
	public function __construct(array $filters = [], $method = 'filter') {
		$this->_filters = $filters;
		$this->_method = $method;
	}



	/**
	 *	Returns all filters.
	 *
	 *	@return array Filters.
	 */
	public function filters() {
		return $this->_filters;
	}



	/**
	 *	Sets all filters.
	 *
	 *	@param array $filters Filters.
	 *	@return Cascade Instance.
	 */
	public function setFilters(array $filters) {
		$this->_filters = $filters;
		return $this;
	}



	/**
	 *	Adds a filter.
	 *
	 *	@param callable|object $filter Filter.
	 *	@return Cascade Instance.
	 */
	public function addFilter($filter) {
		$this->_filters[] = $filter;
		return $this;
	}



	/**
	 *	Returns filtering method.
	 *
	 *	@return string Method.
	 */
	public function method() {
		return $this->_method;
	}



	/**
	 *	Sets filtering method.
	 *
	 *	@param string $method Method.
	 *	@return Cascade Instance.
	 */
	public function setMethod($method) {
		$this->_method = $method;
		return $this;
	}



	/**
	 *	Filters the given value.
	 *
	 *	@param mixed $value Value.
	 *	@param mixed ... Additional arguments to pass to the filters.
	 *	@return mixed Filtered value.
	 */
	public function filter() {
		$arguments = func_get_args();

		if (empty($arguments)) {
			throw new BadMethodCallException(
				'A value to filter is required.'
			);
		}

		$value = &$arguments[0];

		foreach ($this->_filters as $filter) {
			if (!is_callable($filter)) {
				$filter = [$filter, $this->_method];

				if (!is_callable($filter)) {
					continue;
				}
			}

			$value = call_user_func_array($filter, $arguments);
		}

		return $value;
	}
}
