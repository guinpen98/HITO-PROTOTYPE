#ifndef HITO_SCENE_H
#define HITO_SCENE_H

namespace HITO {
	class Scene {
	public:
		virtual ~Scene() {}
;		virtual void update() = 0;
	};
}

#endif // !HITO_SCENE_H
