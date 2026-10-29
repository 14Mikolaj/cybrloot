#include <cassert>
#include <stdexcept>
#include <string>
#include <utility>

#include "Scene.hpp"

using CybrUtil::Terminal;

template <typename Exception, typename Fn>
void expects_exception(Fn&& fn, const std::string& message) {
    try {
        fn();
    } catch (const Exception& e) {
        assert(std::string(e.what()).find(message) != std::string::npos);
        return;
    }
    assert(false && "Expected an exception");
}

void test_forward_references_and_resize() {
    Scene scene("forward");
    scene.add_panel(Panel(
        PanelPosition::anchored([](const LayoutContext& ctx) {
            const auto& root = ctx.get("root");
            return Rect{root.right(), root.top(), 20, root.h};
        }), "Visible child", "thin", "Mint", "child"));
    scene.add_panel(Panel(
        PanelPosition::relative(0.0f, 0.0f, 0.25f, 0.5f),
        "Visible root", "thin", "Mint", "root"));

    scene.layout_panels(Terminal{80, 30, 2});
    Rect first_parent = scene.get_panels()[1].get_rect();
    Rect first_child = scene.get_panels()[0].get_rect();
    assert(first_child.left() == first_parent.right());
    assert(first_child.top() == first_parent.top());
    assert(first_child.h == first_parent.h);
    assert(first_child.w == 20);

    scene.layout_panels(Terminal{120, 40, 2});
    Rect next_parent = scene.get_panels()[1].get_rect();
    Rect next_child = scene.get_panels()[0].get_rect();
    assert(next_parent.w != first_parent.w);
    assert(next_child.left() == next_parent.right());
    assert(next_child.h == next_parent.h);
}

void test_duplicate_ids() {
    Scene scene("duplicate");
    scene.add_panel(Panel(PanelPosition::absolute(1, 1, 8, 4), "One", "thin", "Mint", "same"));
    scene.add_panel(Panel(PanelPosition::absolute(1, 1, 8, 4), "Two", "thin", "Mint", "same"));
    expects_exception<std::invalid_argument>(
        [&] { scene.layout_panels(Terminal{80, 30, 2}); }, "Duplicate panel ID: same");
}

void test_same_title_different_ids() {
    Scene scene("same title");
    scene.add_panel(Panel(PanelPosition::absolute(1, 1, 8, 4), "Duplicate", "thin", "Mint", "first"));
    scene.add_panel(Panel(PanelPosition::absolute(1, 1, 8, 4), "Duplicate", "thin", "Mint", "second"));
    scene.layout_panels(Terminal{80, 30, 2});
    assert(scene.get_panels().size() == 2);
}

void test_unknown_id() {
    Scene scene("unknown");
    scene.add_panel(Panel(
        PanelPosition::anchored([](const LayoutContext& ctx) { return ctx.get("absent"); }),
        "Child", "thin", "Mint", "child"));
    expects_exception<std::invalid_argument>(
        [&] { scene.layout_panels(Terminal{80, 30, 2}); }, "Unknown panel ID: absent");
}

void test_cycle() {
    Scene scene("cycle");
    scene.add_panel(Panel(
        PanelPosition::anchored([](const LayoutContext& ctx) { return ctx.get("b"); }),
        "A", "thin", "Mint", "a"));
    scene.add_panel(Panel(
        PanelPosition::anchored([](const LayoutContext& ctx) { return ctx.get("a"); }),
        "B", "thin", "Mint", "b"));
    expects_exception<std::logic_error>(
        [&] { scene.layout_panels(Terminal{80, 30, 2}); }, "Circular panel layout dependencies");
}

void test_small_terminal() {
    Scene scene("small");
    scene.add_panel(Panel(PanelPosition::relative(0.5f, 0.5f, 0.2f, 0.2f),
                          "Tiny", "thin", "Mint", "tiny"));
    scene.layout_panels(Terminal{1, 1, 2});
    const Rect r = scene.get_panels()[0].get_rect();
    assert(r.w >= 2 && r.h >= 2);
}

int main() {
    test_forward_references_and_resize();
    test_duplicate_ids();
    test_same_title_different_ids();
    test_unknown_id();
    test_cycle();
    test_small_terminal();
}
