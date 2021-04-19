#ifndef RENDEROBJ
#define RENDEROBJ

using namespace std;

class RenderObj {

	public:

    virtual void init() =0;
		virtual void dessiner() =0;
};

#endif
