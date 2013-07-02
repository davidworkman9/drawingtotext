#include "InputFormatDWG.h"

InputFormatDWG::InputFormatDWG(const char * inputFilename) {
	this->dwg = new Dwg_Data();
	int errno = dwg_read_file((char *)inputFilename, this->dwg);
	if (errno) {
		fprintf(stderr, "Could not open DWG. Returned error code: $d\n", errno);
		delete this->dwg;
	}

	this->currentBlockX = 0;
	this->currentBlockY = 0;

}

void InputFormatDWG::readFeaturesInto(OutputFormat * outputHandler) {
	if (!this->dwg) return;
	
	// Pull in actual data now...
	this->output = outputHandler;
	
	Dwg_Object_BLOCK_CONTROL * ctrl = this->dwg->object[0].tio.object->tio.BLOCK_CONTROL;
	for (int i = 0; i < ctrl->num_entries; i++) {
		this->dumpBlock(ctrl->block_headers[i]);
	}	
	
	this->dumpBlock(ctrl->model_space);
	this->dumpBlock(ctrl->paper_space);	
	
	// Don't delete output format - caller can do that
	this->output = NULL;
	dwg_free(this->dwg);
}

void InputFormatDWG::dumpBlock(Dwg_Object_Ref * block) {
	if (!block) return;
	if (!block->obj) return;
	if (!block->obj->tio.object) return;

	Dwg_Object_BLOCK_HEADER * header = block->obj->tio.object->tio.BLOCK_HEADER;
	Dwg_Object * obj = get_first_owned_object(block->obj, header);
	while (obj) {
		if (obj->type == DWG_TYPE_TEXT) {
			Dwg_Entity_TEXT * text = obj->tio.entity->tio.TEXT;

			OutputFeaturePoint * newPoint = new OutputFeaturePoint(text->insertion_pt.x + this->currentBlockX, text->insertion_pt.y + this->currentBlockY, 0);
			this->output->addText(*newPoint, (const char *)text->text_value);
			delete newPoint;
		}
		obj = get_next_owned_object(block->obj, obj, header);
	}
}
