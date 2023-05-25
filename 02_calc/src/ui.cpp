#include "ui.h"
#include <cmath>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/screen/string.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
  
namespace calc
{
    using namespace ftxui;
    struct Operation {
        std::string expr;
        std::string result;
        // Дополнительные поля, описывающие операцию
    };
    class MyComponent {
    public:
        void AddOperation(const Operation& operation) {
            history_.push_back(operation);
        }

        std::vector<Operation> GetHistory() const {
            return history_;
        }
    private:
        std::vector<Operation> history_;
    };

    MyComponent component;

    std::vector<int> demo_triangle(int width, int height)
    {
        std::vector<int> output(width);
        for (int x = 0; x < width; ++x) {
            float y = 0;
            y += 0.3f * sin(x * 0.1f);        // NOLINT
            y *= height;                                // NOLINT
            // y += 0.5f * height;                         // NOLINT
            output[x] = static_cast<int>(y);
        }
    return output;
    
  }

    double Function(double x) {
        return sin(x);
    }

    Element UI::render_input()
    {
        return hbox(text(" Expression: "), expression_input_box->Render());
    }

    
    Element UI::render_output() {
        std::string result = "Your expression: ";
        result.append(logic_ref.expression);
        
        std::string result2 = "Result: ";
        if (logic_ref.expression == "plot")
        {   
        //     int graph_width = 50;
        //     int graph_height = 20;

        // // Минимальное и максимальное значение x.
        //     double x_min = -5.0;
        //     double x_max = 5.0;

        // // Минимальное и максимальное значение y.
        //     double y_min = -1.0;
        //     double y_max = 1.0;
        //     for (int i = 0; i < graph_width; ++i) {
        //         double x = x_min + (x_max - x_min) * i / graph_width;
        //         double y = Function(x);
        //         graph.plot(x, y);
        //     }
        //     return hbox(text(L"Graph:"), graph.Render());
            return graph(std::ref(demo_triangle)) | color(Color::Khaki3);
        } else if (logic_ref.expression == "history"){
            std::vector<Operation> history = component.GetHistory();
            std::vector<ftxui::Element> hboxArray = {};
            for (const auto& operation : history) {
                hboxArray.push_back(hbox({text(operation.expr),text("="),text(operation.result)}));  
            }
            return vbox(hboxArray);
        }
        else
        {
            std::string otv = logic_ref.process_math();
            result2.append(otv);
            component.AddOperation(Operation { logic_ref.expression,otv});
            return vbox({text(result), separator(), text(result2)});
        }
    }

    bool UI::process_events(Event event)
    {
        if (event == Event::Escape)
        {
            screen.ExitLoopClosure()();
            return true;
        }
        else if (event == Event::Return)
        {
            element_output = render_output();
            logic_ref.expression.clear();
            return true;
        }
        return false;
    }

    void UI::start()
    {
        auto component = Container::Vertical({expression_input_box});

        auto renderer = Renderer(component, [&]
                                 { return vbox({render_input(), separator(), element_output}) | border; });

        renderer |= CatchEvent([&](Event event)
                               { return process_events(event); });

        screen.Loop(renderer);
    }

} // namespace calc