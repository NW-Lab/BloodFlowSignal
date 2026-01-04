#!/usr/bin/env python3
"""
ICS-43434 Microphone Case Generator
血流計測用マイクケースの3Dモデル生成スクリプト

このスクリプトは、CadQueryを使用してICS-43434マイク用の
血流計測ケースを生成します。
"""

import cadquery as cq
from pathlib import Path

# 設計パラメータ
# ベース部（皮膚接触部）
BASE_DIAMETER = 30.0  # ベース部直径 (mm)
BASE_HEIGHT = 10.0    # ベース部高さ (mm)

# 持ち手部
HANDLE_DIAMETER = 20.0  # 持ち手直径 (mm)
HANDLE_HEIGHT = 40.0   # 持ち手高さ (mm)

# マイク基板収納部
PCB_WIDTH = 17.0      # 基板幅 (mm)
PCB_LENGTH = 13.5     # 基板長さ (mm)
PCB_THICKNESS = 2.5   # 基板厚さ + 余裕 (mm)
PCB_OFFSET_Z = 2.0    # 基板底面からの高さ (mm)

# 音孔
PORT_DIAMETER = 6.0   # 音孔直径 (mm)
PORT_DEPTH = 3.0      # 音孔の深さ (mm)

# 壁厚
WALL_THICKNESS = 2.0  # 壁の厚さ (mm)

# ケーブル切り欠き
CABLE_NOTCH_WIDTH = 6.0   # ケーブル切り欠き幅 (mm)
CABLE_NOTCH_HEIGHT = 4.0  # ケーブル切り欠き高さ (mm)

# フィレット
FILLET_RADIUS = 1.0   # 面取り半径 (mm)


def create_microphone_case():
    """
    マイクケースの3Dモデルを生成
    """
    
    # ベース部（円筒形）を作成
    base = (
        cq.Workplane("XY")
        .circle(BASE_DIAMETER / 2)
        .extrude(BASE_HEIGHT)
    )
    
    # 持ち手部（円筒形）を作成
    handle = (
        cq.Workplane("XY")
        .workplane(offset=BASE_HEIGHT)
        .circle(HANDLE_DIAMETER / 2)
        .extrude(HANDLE_HEIGHT)
    )
    
    # ベースと持ち手を結合
    case = base.union(handle)
    
    # マイク基板収納部をくり抜く（上面から）
    case = (
        case
        .faces(">Z")
        .workplane()
        .rect(PCB_WIDTH, PCB_LENGTH)
        .cutBlind(-PCB_THICKNESS)
    )
    
    # 音孔を底面から開ける
    case = (
        case
        .faces("<Z")
        .workplane()
        .circle(PORT_DIAMETER / 2)
        .cutBlind(PORT_DEPTH)
    )
    
    # ケーブル用の切り欠きを作成（側面）
    cable_notch = (
        cq.Workplane("XZ")
        .workplane(offset=BASE_DIAMETER / 2)
        .rect(CABLE_NOTCH_WIDTH, CABLE_NOTCH_HEIGHT)
        .extrude(-WALL_THICKNESS * 2)
    )
    
    # ケーブル切り欠きを適用
    case = case.cut(cable_notch.translate((0, 0, BASE_HEIGHT - CABLE_NOTCH_HEIGHT / 2)))
    
    # エッジを面取り（持ちやすく、皮膚への刺激を軽減）
    try:
        case = case.edges("|Z").fillet(FILLET_RADIUS)
    except:
        print("Warning: Some edges could not be filleted")
    
    return case


def create_microphone_lid():
    """
    マイク固定用の蓋を生成（オプション）
    """
    
    # 蓋の基本形状
    lid = (
        cq.Workplane("XY")
        .rect(PCB_WIDTH - 0.5, PCB_LENGTH - 0.5)
        .extrude(1.5)
    )
    
    # 中央に穴を開ける（マイク部分）
    lid = (
        lid
        .faces(">Z")
        .workplane()
        .circle(PORT_DIAMETER / 2)
        .cutThruAll()
    )
    
    return lid


def main():
    """
    メイン処理：3Dモデルを生成してエクスポート
    """
    
    print("Generating ICS-43434 Microphone Case...")
    
    # 出力ディレクトリを作成
    output_dir = Path(__file__).parent
    output_dir.mkdir(parents=True, exist_ok=True)
    
    # ケース本体を生成
    case = create_microphone_case()
    
    # STLファイルとしてエクスポート
    stl_path = output_dir / "microphone_case.stl"
    print(f"Exporting STL: {stl_path}")
    cq.exporters.export(case, str(stl_path))
    
    # STEP形式でエクスポート（Fusion 360で編集可能）
    step_path = output_dir / "microphone_case.step"
    print(f"Exporting STEP: {step_path}")
    cq.exporters.export(case, str(step_path))
    
    # 蓋を生成
    lid = create_microphone_lid()
    
    # 蓋をSTLとしてエクスポート
    lid_stl_path = output_dir / "microphone_lid.stl"
    print(f"Exporting Lid STL: {lid_stl_path}")
    cq.exporters.export(lid, str(lid_stl_path))
    
    # 蓋をSTEP形式でエクスポート
    lid_step_path = output_dir / "microphone_lid.step"
    print(f"Exporting Lid STEP: {lid_step_path}")
    cq.exporters.export(lid, str(lid_step_path))
    
    print("\nGeneration complete!")
    print(f"Files saved to: {output_dir}")
    print("\nGenerated files:")
    print(f"  - {stl_path.name} (Case - for 3D printing)")
    print(f"  - {step_path.name} (Case - for Fusion 360)")
    print(f"  - {lid_stl_path.name} (Lid - for 3D printing)")
    print(f"  - {lid_step_path.name} (Lid - for Fusion 360)")
    
    # 設計パラメータを表示
    print("\nDesign Parameters:")
    print(f"  Base diameter: {BASE_DIAMETER} mm")
    print(f"  Base height: {BASE_HEIGHT} mm")
    print(f"  Handle diameter: {HANDLE_DIAMETER} mm")
    print(f"  Handle height: {HANDLE_HEIGHT} mm")
    print(f"  Total height: {BASE_HEIGHT + HANDLE_HEIGHT} mm")
    print(f"  PCB cavity: {PCB_WIDTH} x {PCB_LENGTH} x {PCB_THICKNESS} mm")
    print(f"  Port diameter: {PORT_DIAMETER} mm")


if __name__ == "__main__":
    main()
