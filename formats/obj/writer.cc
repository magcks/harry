/*
 * Copyright (C) 2017, Max von Buelow
 * TU Darmstadt - Graphics, Capture and Massively Parallel Computing
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD 3-Clause license. See the LICENSE.txt file for details.
 */

#include <vector>

#include "writer.h"

#include "structs/mixing.h"
#include "structs/types.h"

namespace obj {
namespace writer {

void write(std::ostream &os, const std::string &dir, mesh::Mesh &mesh)
{
	os << "# decompressed using harry mesh compressor" << std::endl << std::endl;

	std::vector<bool> isset_pos(mesh.attrs.size(), false), isset_tex(mesh.attrs.size(), false), isset_normal(mesh.attrs.size(), false);
	for (int i = 0; i < mesh.attrs.num_regs_face(); ++i) {
		for (int j = 0; j < mesh.attrs.num_bindings_corner_reg(i); ++j) {
			mesh::listidx_t l = mesh.attrs.binding_reg_cornerlist(i, j);
			if (mesh.attrs[l].interps().has(mixing::TEX)) isset_tex[l] = true;
			if (mesh.attrs[l].interps().has(mixing::NORMAL)) isset_normal[l] = true;
		}
	}
	for (int i = 0; i < mesh.attrs.num_regs_vtx(); ++i) {
		for (int j = 0; j < mesh.attrs.num_bindings_vtx_reg(i); ++j) {
			mesh::listidx_t l = mesh.attrs.binding_reg_vtxlist(i, j);
			if (mesh.attrs[l].interps().has(mixing::POS)) isset_pos[l] = true;
		}
	}

	os << "# vertex definitions and vertex attributes" << std::endl;
	for (mesh::vtxidx_t i = 0; i < mesh.num_vtx(); ++i) {
		mesh::regidx_t r = mesh.attrs.vtx2reg(i);
		os << "v";
		int cnt = 0;
		for (int j = 0; j < mesh.attrs.num_bindings_vtx_reg(r); ++j) {
			mesh::listidx_t l = mesh.attrs.binding_reg_vtxlist(r, j);
			if (isset_pos[l]) {
				mixing::View e = mesh.attrs[l][mesh.attrs.binding_vtx_attr(i, j)];
				const mixing::Interps &in = mesh.attrs[l].interps();
				for (int k = 0; k < in.len(mixing::POS); ++k) {
					if (cnt++ >= 4) break;
					os << " ";
					e.print(os, in.off(mixing::POS) + k);
				}
				for (int k = 0; k < in.len(mixing::COLOR); ++k) {
					if (cnt++ >= 8) break;
					os << " ";
					e.print(os, in.off(mixing::COLOR) + k);
				}
				break;
			}
		}
		os << std::endl;
	}
	os << std::endl;

	os << "# corner attributes" << std::endl;
	os << "# - texture coordinates" << std::endl;
	std::vector<mesh::attridx_t> tex_off(mesh.attrs.size(), 0);
	mesh::attridx_t last = 0;
	for (int j = 0; j < isset_tex.size(); ++j) {
		if (!isset_tex[j]) continue;
		tex_off[j] = last;
		last += mesh.attrs[j].size();
		const mixing::Interps &in = mesh.attrs[j].interps();
		for (int i = 0; i < mesh.attrs[j].size(); ++i) {
			mixing::View e = mesh.attrs[j][i];

			os << "vt";
			for (int k = 0; k < std::min(4, in.len(mixing::TEX)); ++k) {
				os << " ";
				e.print(os, in.off(mixing::TEX) + k);
			}
			os << std::endl;
		}
	}
	os << std::endl;

	os << "# - normals" << std::endl;
	std::vector<mesh::attridx_t> normal_off(mesh.attrs.size(), 0);
	for (int j = 0; j < isset_normal.size(); ++j) {
		if (!isset_normal[j]) continue;
		normal_off[j] = last;
		last += mesh.attrs[j].size();
		const mixing::Interps &in = mesh.attrs[j].interps();
		for (int i = 0; i < mesh.attrs[j].size(); ++i) {
			mixing::View e = mesh.attrs[j][i];
			os << "vn ";
			for (int k = 0; k < std::min(4, in.len(mixing::NORMAL)); ++k) {
				os << " ";
				e.print(os, in.off(mixing::NORMAL) + k);
			}
			os << std::endl;
		}
	}
	os << std::endl;

	os << "# faces" << std::endl;
	for (mesh::faceidx_t i = 0; i < mesh.attrs.num_face(); ++i) {
		mesh::regidx_t r = mesh.attrs.face2reg(i);
		uint8_t ne = mesh.conn.num_edges(i);
		os << "f";
		mesh::listidx_t a_tex = std::numeric_limits<mesh::listidx_t>::max(), a_normal = std::numeric_limits<mesh::listidx_t>::max();
		for (int a = 0; a < mesh.attrs.num_bindings_corner_reg(r); ++a) {
			mesh::listidx_t as = mesh.attrs.binding_reg_cornerlist(r, a);
			if (isset_tex[as]) a_tex = a;
			if (isset_normal[as]) a_normal = a;
		}
		for (int j = 0; j < ne; ++j) {
			os << ' ' << (mesh.conn.org(i, j) + 1);

			if (a_tex != std::numeric_limits<mesh::listidx_t>::max()) {
				os << '/' << (tex_off[mesh.attrs.binding_reg_cornerlist(r, a_tex)] + mesh.attrs.binding_corner_attr(i, j, a_tex) + 1);
			}
			if (a_normal != std::numeric_limits<mesh::listidx_t>::max()) {
				if (a_tex == std::numeric_limits<mesh::listidx_t>::max()) os << '/';
				os << '/' << (normal_off[mesh.attrs.binding_reg_cornerlist(r, a_normal)] + mesh.attrs.binding_corner_attr(i, j, a_normal) + 1);
			}
		}

		os << std::endl;
	}
}

}
}
