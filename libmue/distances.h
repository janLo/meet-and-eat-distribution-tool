#ifndef MUE_DISTANCES_H
#define MUE_DISTANCES_H

#include <vector>

#include <boost/assert.hpp>


#include <teams.h>


namespace mue {

	typedef float Distance;


	class Distance_matrix
	{
		private:
			std::vector<std::vector<Distance> > _table;
			unsigned int _teamcount;
			Distance     _min_cost;

		public:
			Distance_matrix(int teamcount) noexcept;

			void set_cost(Team_id const source, Team_id const destination, Distance cost);

			Distance lookup(Team_id const source, Team_id const destination) const noexcept
			{
				return _table[source][destination];
			}

			int teamcount() const { return _teamcount; }

			Distance min_cost() const { return _min_cost; }
	};


	class Distance_forecast
	{
		private:
			unsigned _hostcount;
			std::vector<Distance> _second_costs;
			std::vector<Distance> _first_costs;


			static std::vector<Distance>
			_min_costs(Distance_matrix const &distances, unsigned hostcount,
				   unsigned multiply);

			static std::vector<Distance>
			_fill_costs(Distance_matrix const &distances, unsigned hostcount,
				    unsigned multiply, Distance const &offset);

		public:
			Distance_forecast(Distance_matrix const &distances);

			Distance first_move(size_t host_idx) const
			{
				BOOST_ASSERT(host_idx + 1 < _first_costs.size());
				return _first_costs[host_idx + 1];
			}

			Distance second_move(size_t host_idx) const
			{
				BOOST_ASSERT(host_idx + 1 < _second_costs.size());
				return _second_costs[host_idx + 1];
			}
	};
}


#endif
