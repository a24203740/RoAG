/* Tolerance

 * By Song Jingyi

 * A friend bought a piece of fabric with a green background and white squares. When she showed it to us, a classmate who was very interested in Go said:

 * "Ah, it looks like a Go board."

 * "I think it resembles manuscript paper," I said.

 * "It really looks like pieces of green bean cake," added another classmate nicknamed "Big Eater."

 * We couldn't help but burst into laughter. The same piece of fabric evoked different impressions in each of us. That friend quickly wrapped the fabric in paper; to her, the fabric was just fabric—not a Go board, not manuscript paper, and certainly not green bean cake.

 * Everyone's perspectives differ, influenced by individual personalities and life experiences.

 * If you frequently visit fabric stores, you'll notice that there's rarely a bolt of cloth that no one chooses; in other words, every type of fabric, regardless of its texture or pattern, has its admirers. A shoe store owner once pointed to a pair of rather unattractive shoes in the display window and said, "No matter how ugly the design, someone will like it, so there's no fear of them not selling."

 * People's preferences vary greatly. Some like sour flavors, while others prefer sweet; some enjoy classical music, while others favor pop; some love vibrant colors, while others lean towards simplicity. If we can appreciate these differences and not insist that others share our tastes, we can avoid many unnecessary disputes.

 * In interpersonal interactions, occasional friction often arises from a lack of tolerance; therefore, to reduce conflicts and promote harmony, we must strive to cultivate tolerance.

 * aba0122 request me to put this shit on it.

 */

#include "../core/opengl_drawable.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "glm/trigonometric.hpp"

class Ground : public Drawable {
public:
    Ground() : Drawable() { 
        std::vector<float> vertices;
        int gridSize = 100;
        float tileSize = 1;

        for (int x = 0; x < gridSize; x++) {
            for (int z = 0; z < gridSize; z++) {
                // 計算當前格子的顏色
                bool isWhite = (x + z) % 2 == 0;
                glm::vec3 color = isWhite ? glm::vec3(0x00 / 255.0, 0x00 / 255.0, 0x00 / 255.0) : glm::vec3(0xFF / 255.0, 0xFF / 255.0, 0xFF / 255.0);

                // 計算四個角落的座標
                float x0 = x * tileSize;
                float z0 = z * tileSize;
                float x1 = (x + 1) * tileSize;
                float z1 = (z + 1) * tileSize;

                // 定義兩個三角形來繪製這個格子
                float quad[] = {
                    x0, 0.0f, z0, color.x, color.y, color.x,  // 左下
                    x1, 0.0f, z0, color.x, color.y, color.z,  // 右下
                    x1, 0.0f, z1, color.x, color.y, color.z,  // 右上
                    x0, 0.0f, z0, color.x, color.y, color.z,  // 左下
                    x1, 0.0f, z1, color.x, color.y, color.z,  // 右上
                    x0, 0.0f, z1, color.x, color.y, color.z   // 左上
                };

                // 加入 vector
                vertices.insert(vertices.end(), std::begin(quad), std::end(quad));
            }
        }

        SetVertexes(vertices);
    }
};