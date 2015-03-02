<?hh //partial

/**
 *	HHVM port of Félix Girault's Cascade (https://github.com/felixgirault/cascade)
 *	@author Matthias Jouan <matthias.jouan@gmail.com>
 *	@license FreeBSD License (http://opensource.org/licenses/BSD-2-Clause)
 */
 
namespace Cascade;

use PHPUnit_Framework_TestCase as TestCase;



/**
 *
 */
class MultiplyFilter {

	/**
	 *
	 */
	public function __invoke($value, $factor) {
		return $value * $factor;
	}
}



/**
 *
 */
class CascadeTest extends TestCase {

	/**
	 *
	 */
	public $Cascade = null;



	/**
	 *
	 */
	public function setUp() {
		$this->Cascade = new Cascade();
	}



	/**
	 *
	 */
	public function testFilters() {
		$filter = function() {};
		$filters = Vector {$filter};

		$this->assertEquals($this->Cascade, $this->Cascade->setFilters($filters));
		$this->assertEquals($filters, $this->Cascade->filters());

		$filters[] = $filter;

		$this->assertEquals($this->Cascade, $this->Cascade->addFilter($filter));
		$this->assertEquals($filters, $this->Cascade->filters());
	}



	/**
	 *
	 */
	public function testFilter() {
		$this->setExpectedException('BadMethodCallException');
		$this->Cascade->filter();
	}



	/**
	 *
	 */
	public function testFilterWithFunction() {
		$filter = function($value, $increment) {
			return $value + $increment;
		};

		$this->Cascade->addFilter($filter);
		$this->Cascade->addFilter($filter);

		$this->assertEquals(6, $this->Cascade->filter(2, 2));
	}



	/**
	 *
	 */
	public function testFilterWithMethod() {
		$Filter = new MultiplyFilter();

		$this->Cascade->addFilter($Filter);
		$this->Cascade->addFilter($Filter);

		$this->assertEquals(8, $this->Cascade->filter(2, 2));
	}
}
