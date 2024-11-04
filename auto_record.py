import pandas as pd
import yaml
import os
from datetime import datetime

# Define file paths
excel_file_path = 'records.xlsx'
mkdocs_file_path = 'mkdocs.yml'
index_md_path = '.\\docs\\index.md'
docs_path = '.\\docs'

# Load Excel data
df = pd.read_excel(excel_file_path)

# Function to ensure directory exists
def ensure_dir(file_path):
    if not os.path.exists(file_path):
        os.makedirs(file_path)

# Update mkdocs.yml
with open(mkdocs_file_path, 'r') as file:
    mkdocs_data = yaml.safe_load(file)

# Reset ICPC and CodeForce training navs
mkdocs_data['nav'][1]['ICPC-Training'] = []
mkdocs_data['nav'][2]['CodeForce-Training'] = []

# Function to process each row and update files
def process_row(row):
    folder_path = os.path.join(docs_path, row['category'], row['date'].strftime('%Y%m%d'))
    file_path = os.path.join(folder_path, 'training.md')
    
    # Update mkdocs.yml
    date_str = row['date'].strftime('%d/%m/%Y')
    rel_path = os.path.join(row['category'], row['date'].strftime('%Y%m%d'), 'training.md').replace('\\', '/')
    if row['category'].startswith('icpc'):
        mkdocs_data['nav'][1]['ICPC-Training'].append({date_str: rel_path})
    else:
        mkdocs_data['nav'][2]['CodeForce-Training'].append({date_str: rel_path})
    
    # Ensure the directory exists
    ensure_dir(folder_path)
    
    # Create or update the Markdown file if it doesn't exist
    if not os.path.exists(file_path):
        with open(file_path, 'w') as md_file:
            md_file.write(f"# {row['contest name']}\n\n")
            md_file.write(f"Virtual Contest: [{row['contest name']}]({row['contest link']})\n\n")
            md_file.write(f"Solutions: [{row['solution link']}]({row['solution link']})\n\n")
            md_file.write("# Submissions\n")

# Process each row in the DataFrame
df['date'] = pd.to_datetime(df['date'], format='%Y%m%d')
df.apply(process_row, axis=1)

# Save the updated mkdocs.yml file
with open(mkdocs_file_path, 'w') as file:
    yaml.safe_dump(mkdocs_data, file, sort_keys=False)

# Update the index.md file
with open(index_md_path, 'w') as index_md:
    index_md.write("# WrongAnswer2 Training Records\n\n")
    index_md.write("## Team members\n\nEric, Jun, Kenny\n\n")
    index_md.write("### Contests\n\n- [Ieeextreme 18.0](https://csacademy.com/ieeextreme18/)   \n\n    - Rank 475 / 8785 (Score: 1070.39) Top 5.4%\n\n- Ieeextreme 17.0 \n\n### Upcoming Contests\n\n\n")
    index_md.write("### ICPC Training\n\n")
    for item in mkdocs_data['nav'][1]['ICPC-Training']:
        for date, path in item.items():
            index_md.write(f"- [{date}]({path})\n")
    index_md.write("\n### CodeForce Training\n\n")
    for item in mkdocs_data['nav'][2]['CodeForce-Training']:
        for date, path in item.items():
            index_md.write(f"- [{date}]({path})\n")

