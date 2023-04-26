#include <pybind11/pybind11.h>
#include <algorithm>
#include <pybind11/stl.h>

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

#include <vector>


std::vector<int> signal_source(std::vector<int>signal_open, std::vector<int> signal_limit, int second)
	{
		sort(signal_open.begin(), signal_open.end());
		sort(signal_limit.begin(), signal_limit.end());
		
		int open_lenth = signal_open.size();
		int limit_lenth = signal_limit.size();

		std::vector<int> open_limit;
		std::vector<int> open_result(signal_open.size());

		for (int i = 0; i < open_lenth; i++)
		{
			for (int j = 0; j < limit_lenth; j++)
			{
				if (signal_open[i] < signal_limit[j])
				{
					break;
				}
				if (signal_open[i] >= signal_limit[j] && signal_open[i] <= signal_limit[j] + second)
				{
					open_limit.push_back(signal_open[i]);
					break;
				}
			}
		}

		auto it = set_difference(signal_open.begin(), signal_open.end(), open_limit.begin(), open_limit.end(), open_result.begin());
		open_result.resize(it - open_result.begin());
		
		unique(open_result.begin(), open_result.end()+1);

		return open_result;
		
	}



namespace py = pybind11;

PYBIND11_MODULE(cpp_compute, m) {
    m.doc() = R"pbdoc(
        Pybind11 example plugin
        -----------------------

        .. currentmodule:: cpp_compute

        .. autosummary::
           :toctree: _generate

           signal_source
    )pbdoc";
    m.def("signal_source", &signal_source);


#ifdef VERSION_INFO
    m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
    m.attr("__version__") = "dev";
#endif
}
