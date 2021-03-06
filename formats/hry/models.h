/*
 * Copyright (C) 2017, Max von Buelow
 * TU Darmstadt - Graphics, Capture and Massively Parallel Computing
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD 3-Clause license. See the LICENSE.txt file for details.
 */

#pragma once

#include <vector>

#include "arith/coder.h"
#include "arith/model.h"
#include "arith/stat_adaptive.h"
#include "cbm/base.h"

namespace hry {

enum AttrType { DATA, HIST, LHIST };

template <typename TF = uint64_t>
struct CBMInitModel : arith::Model<TF> {
	arith::AdaptiveStatisticsModule<> stat;

	CBMInitModel() : stat(cbm::ILAST + 1)
	{
		for (int i = cbm::IFIRST; i <= cbm::ILAST; ++i) {
			stat.init(i);
		}
	}

	void enc(arith::Encoder<TF> &coder, const unsigned char *s, int n)
	{
		// TODO correct cast for s
		const cbm::INITOP *sc = (const cbm::INITOP*)s;
		coder(this->stat, *sc);
		this->stat.inc(*sc);
	}
	void dec(arith::Decoder<TF> &coder, unsigned char *s, int n)
	{
		cbm::INITOP *sc = (cbm::INITOP*)s;
		*sc = (cbm::INITOP)coder(this->stat);
		this->stat.inc(*sc);
	}
};

template <int MAXORDER, typename TF = uint64_t>
struct CBMModel : arith::Model<TF> {
	arith::AdaptiveStatisticsModule<> stat;
	TF c;
	TF c_newvtx_i[MAXORDER], c_connfwd_i[MAXORDER];
	int o;

	CBMModel() : stat(cbm::LAST + 1)
	{
		for (int i = cbm::FIRST; i <= cbm::LAST; ++i) {
			stat.init(i);
		}

		c = 2;
		for (int i = 0; i < MAXORDER; ++i) {
			c_newvtx_i[i] = 1;
			c_connfwd_i[i] = 1;
		}
	}

	void order(int _o)
	{
		o = _o;
	}

	void enc(arith::Encoder<TF> &coder, const unsigned char *s, int n)
	{
		const cbm::OP *sc = (const cbm::OP*)s;
		this->set_orderfreqs();
		coder(this->stat, *sc);
		this->inc(*sc);
	}

	void dec(arith::Decoder<TF> &coder, unsigned char *s, int n)
	{
		cbm::OP *sc = (cbm::OP*)s;
		this->set_orderfreqs();
		*sc = (cbm::OP)coder(this->stat);
		this->inc(*sc);
	}

private:
	void set_orderfreqs()
	{
		int i = order2idx(o);
		TF newvtx_scaled = c_newvtx_i[i] * c / (c_newvtx_i[i] + c_connfwd_i[i]);
		TF connfwd_scaled = c - newvtx_scaled;

		stat.set(cbm::NEWVTX, newvtx_scaled);
		stat.set(cbm::CONNFWD, connfwd_scaled);
	}

	int order2idx(int o) const
	{
		--o;
		return o < MAXORDER ? o : MAXORDER - 1;
	}

	void inc(arith::AdaptiveStatisticsModule<>::SymType s)
	{
		int i = order2idx(o);
		if (s == cbm::NEWVTX) {
			++c;
			++c_newvtx_i[i];
		} else if (s == cbm::CONNFWD) {
			++c;
			++c_connfwd_i[i];
		} else {
			stat.inc(s);
		}
	}
};

template <typename S, typename TF = uint64_t>
struct ModelVector : std::vector<arith::Model<TF>*>
{
	const mixing::Fmt &fmt;

	ModelVector(const mixing::Fmt &_fmt) : fmt(_fmt)
	{
		for (int i = 0; i < fmt.size(); ++i) {
			arith::Model<TF> *model;
			switch (fmt.stype(i)) {
			case mixing::FLOAT:  model = new arith::ModelMult<uint32_t, S, TF>(); break;
			case mixing::DOUBLE: model = new arith::ModelMult<uint64_t, S, TF>(); break;
			case mixing::ULONG:  model = new arith::ModelMult<uint64_t, S, TF>(); break;
			case mixing::LONG:   model = new arith::ModelMult<int64_t,  S, TF>(); break;
			case mixing::UINT:   model = new arith::ModelMult<uint32_t, S, TF>(); break;
			case mixing::INT:    model = new arith::ModelMult<int32_t,  S, TF>(); break;
			case mixing::USHORT: model = new arith::ModelMult<int16_t,  S, TF>(); break;
			case mixing::SHORT:  model = new arith::ModelMult<uint16_t, S, TF>(); break;
			case mixing::UCHAR:  model = new arith::ModelMult<int8_t,   S, TF>(); break;
			case mixing::CHAR:   model = new arith::ModelMult<uint8_t,  S, TF>(); break;
			}
			this->push_back(model);
		}
	}

	ModelVector(const ModelVector<S, TF>&) = delete;
	ModelVector<S, TF> &operator=(const ModelVector<S, TF>&) = delete;

	~ModelVector()
	{
		for (int i = 0; i < fmt.size(); ++i) {
			switch (fmt.stype(i)) {
			case mixing::FLOAT:  delete (arith::ModelMult<uint32_t, S, TF>*)(*this)[i]; break;
			case mixing::DOUBLE: delete (arith::ModelMult<uint64_t, S, TF>*)(*this)[i]; break;
			case mixing::ULONG:  delete (arith::ModelMult<uint64_t, S, TF>*)(*this)[i]; break;
			case mixing::LONG:   delete (arith::ModelMult<int64_t,  S, TF>*)(*this)[i]; break;
			case mixing::UINT:   delete (arith::ModelMult<uint32_t, S, TF>*)(*this)[i]; break;
			case mixing::INT:    delete (arith::ModelMult<int32_t,  S, TF>*)(*this)[i]; break;
			case mixing::USHORT: delete (arith::ModelMult<int16_t,  S, TF>*)(*this)[i]; break;
			case mixing::SHORT:  delete (arith::ModelMult<uint16_t, S, TF>*)(*this)[i]; break;
			case mixing::UCHAR:  delete (arith::ModelMult<int8_t,   S, TF>*)(*this)[i]; break;
			case mixing::CHAR:   delete (arith::ModelMult<uint8_t,  S, TF>*)(*this)[i]; break;
			}
		}
	}

	void enc(arith::Encoder<TF> &coder, mixing::View v)
	{
		for (int i = 0; i < fmt.size(); ++i) {
			(*this)[i]->enc(coder, v.data(i), v.bytes(i));
		}
	}

	void dec(arith::Decoder<TF> &coder, mixing::View v)
	{
		for (int i = 0; i < fmt.size(); ++i) {
			(*this)[i]->dec(coder, v.data(i), v.bytes(i));
		}
	}
};

struct HryModels {
	CBMModel<8> conn_op;
	CBMInitModel<> conn_iop;
	arith::ModelMult<uint32_t, arith::AdaptiveStatisticsModule<>> conn_elem;
	arith::ModelMult<uint16_t, arith::AdaptiveStatisticsModule<>> conn_part;
	arith::ModelMult<uint32_t, arith::AdaptiveStatisticsModule<>> conn_vert;
	arith::ModelMult<uint16_t, arith::AdaptiveStatisticsModule<>> conn_numtri;
	arith::ModelMult<uint16_t, arith::AdaptiveStatisticsModule<>> conn_regface, conn_regvtx;

	std::vector<arith::ModelMult<uint8_t, arith::AdaptiveStatisticsModule<>>*> attr_type;
	std::vector<arith::ModelMult<uint32_t, arith::AdaptiveStatisticsModule<>>*> attr_ghist;
	std::vector<arith::ModelMult<uint16_t, arith::AdaptiveStatisticsModule<>>*> attr_lhist;
	std::vector<ModelVector<arith::AdaptiveStatisticsModule<>>*> attr_data;

	HryModels(mesh::Mesh &mesh) :
		conn_numtri(false), conn_regface(false), conn_regvtx(false)
	{
		for (int i = 0; i < mesh.attrs.size(); ++i) {
			attr_type.push_back(new arith::ModelMult<uint8_t, arith::AdaptiveStatisticsModule<>>(false));
			attr_type.back()->init(DATA); attr_type.back()->init(HIST);
			if (mesh.attrs[i].target == mesh::attr::CORNER) attr_type.back()->init(LHIST);
			attr_ghist.push_back(new arith::ModelMult<uint32_t, arith::AdaptiveStatisticsModule<>>());
			attr_lhist.push_back(new arith::ModelMult<uint16_t, arith::AdaptiveStatisticsModule<>>());
			attr_data.push_back(new ModelVector<arith::AdaptiveStatisticsModule<>>(mesh.attrs[i].fmt()));
		}

		for (mesh::Faces::EdgeIterator it = mesh.faces.edge_begin(); it != mesh.faces.edge_end(); ++it) {
			conn_numtri.init((uint16_t)(*it - 2));
		}
		for (int i = 0; i < mesh.attrs.num_regs_face(); ++i) {
			conn_regface.init(i);
		}
		for (int i = 0; i < mesh.attrs.num_regs_vtx(); ++i) {
			conn_regvtx.init(i);
		}
	}

	HryModels(const HryModels&) = delete;
	HryModels &operator=(const HryModels&) = delete;

	~HryModels()
	{
		for (int i = 0; i < attr_data.size(); ++i) {
			delete attr_type[i];
			delete attr_ghist[i];
			delete attr_lhist[i];
			delete attr_data[i];
		}
	}

	void order(int i)
	{
		conn_op.order(i);
	}
};

}
