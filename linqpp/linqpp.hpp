#ifndef LINQPP_HPP_INCLUDED
#define LINQPP_HPP_INCLUDED

#include <iterator>
#include <functional>
#include <type_traits>
#include <vector>
#include <map>

namespace linqpp
{
struct out_of_range_exception {};

	template<typename IT> struct it_seq_p {
		it_seq_p(IT begin, IT end): it(begin), end(end) {}

		using value_type = typename IT::value_type;

		IT it, end;

		bool at_end() const
		{
			return it==end;
		}
		typename IT::value_type get()
		{
			return *it++;
		}
	};

	template<typename S, typename VT> struct transform_seq_p {
		transform_seq_p(S &seq, std::function<VT(typename S::value_type)> f): seq(seq), f(f) {}

		using value_type = typename VT;

		S seq;
		std::function<VT(typename S::value_type)> f;

		bool at_end() const
		{
			return seq.at_end();
		}
		value_type get()
		{
			return f(seq.get());
		}
	};

	template<typename S, typename VT> struct filter_seq_p {
		filter_seq_p(S &seq, std::function<bool(typename S::value_type)> f): seq(seq), f(f) {}

		using value_type = typename VT;

		S seq;
		std::function<VT(typename S::value_type)> f;

		bool at_end() const
		{
			return seq.at_end();
		}
		value_type get()
		{
			auto v = seq.get();
			while (!seq.at_end() && !f(v)) {
				v = seq.get();
			}
			return v;
		}
	};

	template<typename S, typename VT> struct take_seq_p {
		take_seq_p(S &seq, int n): seq(seq), n(n) {}

		using value_type = typename VT;

		S seq;
		int n;

		bool at_end() const
		{
			return n<1;
		}
		value_type get()
		{
			if (--n >= 0) return seq.get();
			else throw out_of_range_exception();
		}
	};


	template<typename SP> struct seq {
		seq(SP sp): sp(sp) {}

		using value_type = typename SP::value_type;

		SP sp;

		bool at_end() const
		{
			return sp.at_end();
		}
		typename SP::value_type get()
		{
			return sp.get();
		}
		seq skip(int n)
		{
			while (n>0) {
				get();
				--n;
			}
			return *this;
		}
		std::vector<value_type> vector()
		{
			std::vector<value_type> vec;
			while (!at_end()) {
				vec.push_back(get());
			}
			return vec;
		}
		template<typename KFT, typename VFT>
		std::map<typename std::invoke_result<KFT, value_type>::type, typename std::invoke_result<VFT, value_type>::type>
		map(KFT kf, VFT vf)
		{
			using key_type = typename std::invoke_result<KFT, value_type>::type;
			using value_type = typename std::invoke_result<VFT, value_type>::type;

			std::map<key_type, value_type> map;
			while (!at_end()) {
				auto r = get();
				map[kf(r)] = vf(r);
			}
			return map;
		}

		template<typename ESP> seq<ESP> ext(std::function<ESP(seq)> make_ext_seq)
		{
			return make_ext_seq(*this);
		}

		template<typename FT> seq<transform_seq_p<seq, typename std::invoke_result<FT, value_type>::type>> transform(FT f)
		{
			using EVT = std::invoke_result<FT, value_type>::type;
			return seq<transform_seq_p<seq, EVT>>(transform_seq_p<seq, EVT>(*this, f));
		}
		template<typename FT> seq<filter_seq_p<seq, value_type>> filter(FT f)
		{
			return seq<filter_seq_p<seq, value_type>>(filter_seq_p<seq, value_type>(*this, f));
		}
		seq<take_seq_p<seq, value_type>> take(int n)
		{
			return seq<take_seq_p<seq, value_type>>(take_seq_p<seq, value_type>(*this, n));
		}
	};

	template<typename CT> seq<it_seq_p<typename CT::const_iterator>> make_seq(CT &c)
	{
		return seq<it_seq_p<typename CT::const_iterator>>(it_seq_p<typename CT::const_iterator>(c.cbegin(), c.cend()));
	}
}
#endif
