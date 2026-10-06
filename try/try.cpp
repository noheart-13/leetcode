// 李萨如图与两个简谐振动合成
// 编译：g++ -std=c++17 lissajous.cpp -O2 -o lissajous
// 运行：lissajous.exe --sample
//      或直接运行后按提示输入参数。

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

constexpr double PI = 3.14159265358979323846;

struct Point {
    double t{};
    double x{};
    double y{};
};

struct Parameters {
    double ax = 1.0;          // x 方向振幅
    double ay = 1.0;          // y 方向振幅
    double fx = 3.0;          // x 方向频率（Hz）
    double fy = 2.0;          // y 方向频率（Hz）
    double phaseX = 0.0;      // x 方向初相位（度）
    double phaseY = 90.0;     // y 方向初相位（度）
    double duration = 2.0;    // 采样时长（秒）
    int samples = 2000;       // 采样点数
};

double degToRad(double degrees) {
    return degrees * PI / 180.0;
}

std::vector<Point> generatePoints(const Parameters& p) {
    std::vector<Point> points;
    points.reserve(static_cast<std::size_t>(p.samples) + 1);

    const double phaseX = degToRad(p.phaseX);
    const double phaseY = degToRad(p.phaseY);
    for (int i = 0; i <= p.samples; ++i) {
        const double t = p.duration * i / p.samples;
        const double x = p.ax * std::sin(2.0 * PI * p.fx * t + phaseX);
        const double y = p.ay * std::sin(2.0 * PI * p.fy * t + phaseY);
        points.push_back({ t, x, y });
    }
    return points;
}

void writeCsv(const std::vector<Point>& points, const std::string& fileName) {
    std::ofstream out(fileName);
    if (!out) throw std::runtime_error("cannot create " + fileName);

    out << "t_seconds,x,y\n" << std::setprecision(12);
    for (const auto& point : points) {
        out << point.t << ',' << point.x << ',' << point.y << '\n';
    }
}

struct Bounds {
    double minX{}, maxX{}, minY{}, maxY{};
};

Bounds getBounds(const std::vector<Point>& points) {
    Bounds b{ std::numeric_limits<double>::max(),
             std::numeric_limits<double>::lowest(),
             std::numeric_limits<double>::max(),
             std::numeric_limits<double>::lowest() };
    for (const auto& point : points) {
        b.minX = std::min(b.minX, point.x);
        b.maxX = std::max(b.maxX, point.x);
        b.minY = std::min(b.minY, point.y);
        b.maxY = std::max(b.maxY, point.y);
    }
    // 给坐标轴留边界，避免轨迹贴在图框上。
    const double dx = std::max(0.05, (b.maxX - b.minX) * 0.08);
    const double dy = std::max(0.05, (b.maxY - b.minY) * 0.08);
    b.minX -= dx; b.maxX += dx;
    b.minY -= dy; b.maxY += dy;
    return b;
}

std::string svgNumber(double value) {
    std::ostringstream text;
    text << std::fixed << std::setprecision(2) << value;
    return text.str();
}

void writeSvg(const std::vector<Point>& points, const Parameters& p,
    const std::string& fileName) {
    constexpr double width = 1200.0;
    constexpr double height = 800.0;
    constexpr double left = 95.0;
    constexpr double right = 35.0;
    constexpr double top = 90.0;
    constexpr double bottom = 75.0;
    const Bounds b = getBounds(points);

    auto sx = [&](double x) {
        return left + (x - b.minX) / (b.maxX - b.minX) * (width - left - right);
        };
    auto sy = [&](double y) {
        return height - bottom - (y - b.minY) / (b.maxY - b.minY) * (height - top - bottom);
        };

    std::ofstream out(fileName);
    if (!out) throw std::runtime_error("cannot create " + fileName);

    out << "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"1200\" height=\"800\" viewBox=\"0 0 1200 800\">\n";
    out << "<rect width=\"100%\" height=\"100%\" fill=\"#ffffff\"/>\n";
    out << "<text x=\"600\" y=\"38\" text-anchor=\"middle\" font-size=\"26\" font-family=\"Arial\">Lissajous curve: x(t)=Ax sin(2πfx t+φx), y(t)=Ay sin(2πfy t+φy)</text>\n";
    out << "<text x=\"600\" y=\"68\" text-anchor=\"middle\" font-size=\"18\" font-family=\"Arial\">Ax=" << p.ax << ", Ay=" << p.ay
        << ", fx=" << p.fx << " Hz, fy=" << p.fy << " Hz, phaseX=" << p.phaseX << " deg, phaseY=" << p.phaseY << " deg</text>\n";
    out << "<rect x=\"" << left << "\" y=\"" << top << "\" width=\"" << width - left - right
        << "\" height=\"" << height - top - bottom << "\" fill=\"#f8fbff\" stroke=\"#2f4f6f\"/>\n";

    // 网格和坐标轴。
    for (int i = 0; i <= 10; ++i) {
        const double x = left + (width - left - right) * i / 10.0;
        const double y = top + (height - top - bottom) * i / 10.0;
        out << "<line x1=\"" << x << "\" y1=\"" << top << "\" x2=\"" << x << "\" y2=\"" << height - bottom << "\" stroke=\"#dce7f2\"/>\n";
        out << "<line x1=\"" << left << "\" y1=\"" << y << "\" x2=\"" << width - right << "\" y2=\"" << y << "\" stroke=\"#dce7f2\"/>\n";
    }
    if (b.minX <= 0 && b.maxX >= 0)
        out << "<line x1=\"" << sx(0) << "\" y1=\"" << top << "\" x2=\"" << sx(0) << "\" y2=\"" << height - bottom << "\" stroke=\"#777\" stroke-width=\"2\"/>\n";
    if (b.minY <= 0 && b.maxY >= 0)
        out << "<line x1=\"" << left << "\" y1=\"" << sy(0) << "\" x2=\"" << width - right << "\" y2=\"" << sy(0) << "\" stroke=\"#777\" stroke-width=\"2\"/>\n";

    out << "<polyline fill=\"none\" stroke=\"#e34234\" stroke-width=\"2.5\" points=\"";
    for (const auto& point : points) out << svgNumber(sx(point.x)) << ',' << svgNumber(sy(point.y)) << ' ';
    out << "\"/>\n";
    out << "<text x=\"600\" y=\"785\" text-anchor=\"middle\" font-size=\"20\" font-family=\"Arial\">x displacement</text>\n";
    out << "<text x=\"20\" y=\"410\" transform=\"rotate(-90 20 410)\" text-anchor=\"middle\" font-size=\"20\" font-family=\"Arial\">y displacement</text>\n";
    out << "</svg>\n";
}

void writeAnimationHtml(const std::vector<Point>& points, const Parameters& p,
    const std::string& fileName) {
    std::ofstream out(fileName);
    if (!out) throw std::runtime_error("cannot create " + fileName);
    const Bounds b = getBounds(points);

    out << "<!doctype html><html lang=\"en\"><meta charset=\"utf-8\"><title>Lissajous animation</title>\n";
    out << "<style>body{font-family:Arial;margin:20px;background:#f4f7fb;color:#17202a} canvas{background:white;border:1px solid #789;max-width:100%;height:auto} button{font-size:16px;padding:7px 18px;margin:8px 0}</style>\n";
    out << "<h2>Lissajous curve animation</h2><p>x(t)=Ax·sin(2πfx t+φx), y(t)=Ay·sin(2πfy t+φy)</p>\n";
    out << "<button onclick=\"restart()\">Replay</button><span id=\"status\"></span><br><canvas id=\"canvas\" width=\"1000\" height=\"680\"></canvas>\n";
    out << "<script>\nconst data=[";
    out << std::setprecision(12);
    for (const auto& point : points) out << "[" << point.x << ',' << point.y << ',' << point.t << "],";
    out << "];const c=document.getElementById('canvas'),ctx=c.getContext('2d'),status=document.getElementById('status');\n";
    out << "const xmin=" << b.minX << ",xmax=" << b.maxX << ",ymin=" << b.minY << ",ymax=" << b.maxY << ";\n";
    out << "const pad=65, W=c.width-2*pad,H=c.height-2*pad;let index=0, timer;\n";
    out << "function X(x){return pad+(x-xmin)/(xmax-xmin)*W}function Y(y){return c.height-pad-(y-ymin)/(ymax-ymin)*H}\n";
    out << "function frame(){ctx.clearRect(0,0,c.width,c.height);ctx.fillStyle='#f8fbff';ctx.fillRect(pad,pad,W,H);ctx.strokeStyle='#dce7f2';ctx.lineWidth=1;for(let i=0;i<=10;i++){let gx=pad+W*i/10,gy=pad+H*i/10;ctx.beginPath();ctx.moveTo(gx,pad);ctx.lineTo(gx,pad+H);ctx.moveTo(pad,gy);ctx.lineTo(pad+W,gy);ctx.stroke()}ctx.strokeStyle='#667';ctx.lineWidth=2;ctx.beginPath();ctx.moveTo(X(0),pad);ctx.lineTo(X(0),pad+H);ctx.moveTo(pad,Y(0));ctx.lineTo(pad+W,Y(0));ctx.stroke();if(index>0){ctx.strokeStyle='#e34234';ctx.lineWidth=2.5;ctx.beginPath();ctx.moveTo(X(data[0][0]),Y(data[0][1]));for(let i=1;i<index;i++)ctx.lineTo(X(data[i][0]),Y(data[i][1]));ctx.stroke();ctx.fillStyle='#1f77b4';ctx.beginPath();ctx.arc(X(data[index-1][0]),Y(data[index-1][1]),5,0,2*Math.PI);ctx.fill()}status.textContent='  t = '+(index?data[index-1][2]:0).toFixed(3)+' s';}\n";
    out << "function animate(){clearInterval(timer);index=0;frame();timer=setInterval(()=>{index+=Math.max(1,Math.floor(data.length/180));if(index>=data.length){index=data.length;clearInterval(timer)}frame()},16)}function restart(){animate()}animate();</script></html>\n";
}

void printUsage(const char* program) {
    std::cout << "Usage:\n  " << program << " --sample\n  " << program << "   (interactive input)\n\n"
        << "The program writes lissajous.csv, lissajous.svg and lissajous_animation.html.\n";
}

int main(int argc, char** argv) {
    Parameters p;
    if (argc > 1 && std::string(argv[1]) == "--help") {
        printUsage(argv[0]);
        return 0;
    }
    if (argc > 1 && std::string(argv[1]) != "--sample") {
        std::cerr << "Unknown option. Use --sample or --help.\n";
        return 1;
    }
    if (argc <= 1) {
        std::cout << "Enter Ax Ay fx fy phaseX(deg) phaseY(deg) duration(seconds) samples:\n> ";
        if (!(std::cin >> p.ax >> p.ay >> p.fx >> p.fy >> p.phaseX >> p.phaseY >> p.duration >> p.samples)) {
            std::cerr << "Invalid input.\n";
            return 1;
        }
    }
    else {
        std::cout << "Using sample parameters: Ax=1, Ay=1, fx=3 Hz, fy=2 Hz, phaseX=0 deg, phaseY=90 deg.\n";
    }

    if (p.ax <= 0 || p.ay <= 0 || p.fx <= 0 || p.fy <= 0 || p.duration <= 0 || p.samples < 100) {
        std::cerr << "Ax, Ay, fx, fy, duration must be positive and samples must be at least 100.\n";
        return 1;
    }

    try {
        const auto points = generatePoints(p);
        writeCsv(points, "lissajous.csv");
        writeSvg(points, p, "lissajous.svg");
        writeAnimationHtml(points, p, "lissajous_animation.html");
        std::cout << "Generated: lissajous.csv, lissajous.svg, lissajous_animation.html\n";
        std::cout << "Equation: x(t) = " << p.ax << " sin(2*pi*" << p.fx << "*t + " << p.phaseX
            << " deg), y(t) = " << p.ay << " sin(2*pi*" << p.fy << "*t + " << p.phaseY << " deg)\n";
    }
    catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
    return 0;
}
