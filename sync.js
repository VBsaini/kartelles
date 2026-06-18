const { Client } = require('@notionhq/client');
const github = require('@actions/github');

const notion = new Client({ auth: process.env.NOTION_TOKEN });
const databaseId = process.env.NOTION_DATABASE_ID;

const tagColors = {
    'Add': 'green_background',
    'Refactor': 'purple_background',
    'Fix': 'red_background',
    'Polish': 'pink_background',
    'Update': 'blue_background',
    'Remove': 'gray_background',
    'Docs': 'orange_background'
};

async function run() {
    try {
        const commits = github.context.payload.commits;
        if (!commits || commits.length === 0) return;

        for (const commit of commits) {
            const rawMessage = commit.message;
            let tag = "Other"; 
            let cleanMessage = rawMessage;

            if (rawMessage.includes(':')) {
                const parts = rawMessage.split(':');
                let rawTag = parts[0].trim();
                tag = rawTag.charAt(0).toUpperCase() + rawTag.slice(1).toLowerCase();
                cleanMessage = parts.slice(1).join(':').trim();
            }

            const pillColor = tagColors[tag] || 'default';

            await notion.pages.create({
                parent: { database_id: databaseId },
                properties: {
                    'Message': { title: [{ text: { content: cleanMessage } }] },
                    'Tag': { select: { name: tag } },
                    'Commit ID': { rich_text: [{ text: { content: commit.id.substring(0, 7) } }] },
                    'Author': { rich_text: [{ text: { content: commit.author.name || 'Unknown' } }] },
                    'Link': { url: commit.url }
                },
                children: [
                    { object: 'block', type: 'heading_3', heading_3: { rich_text: [{ type: 'text', text: { content: 'Commit Details' } }] } },
                    { object: 'block', type: 'paragraph', paragraph: { rich_text: [
                        { type: 'text', text: { content: ` ${tag} ` }, annotations: { bold: true, color: pillColor } },
                        { type: 'text', text: { content: `   ${cleanMessage}` } }
                    ]}},
                    { object: 'block', type: 'divider', divider: {} },
                    { object: 'block', type: 'bulleted_list_item', bulleted_list_item: { rich_text: [
                        { type: 'text', text: { content: '👤 Committer: ' }, annotations: { bold: true, color: 'gray' } },
                        { type: 'text', text: { content: commit.author.name || 'Unknown' } }
                    ]}},
                    { object: 'block', type: 'bulleted_list_item', bulleted_list_item: { rich_text: [
                        { type: 'text', text: { content: '🔗 View on GitHub: ' }, annotations: { bold: true, color: 'gray' } },
                        { type: 'text', text: { content: commit.id.substring(0, 7), link: { url: commit.url } } }
                    ]}}
                ]
            });
        }
    } catch (error) {
        console.error("❌ Sync Failed:", error.body || error.message);
        process.exit(1); 
    }
}
run();
